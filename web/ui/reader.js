/*
 * When the scan button clicked,request for scanning a tag is send.
 * Server scans,responde with EPC message :
 * EPC: XXXXX
 */

/*
 * global variables
 */

var i=0;//count times
var element;
var selected_div;

function loadXML()
{
	var xmlhttp;
	if(window.XMLHttpRequest)
	{//code for IE7+,FIreFox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status=200)
		{
			document.getElementById("").innerHTML=xmlhttp.responseText;
		}
	}
	xmlhttp.open("GET","ajax_info.txt",true);
	xmlhttp.send();
}
   
function scan_tag()
{
	var xmlhttp = new XMLHttpRequest();
	var res;
	var res_epc,res_tid;
	var div=document.getElementById("tag_body");
    var div_new=document.createElement("div");
    var arr;
	i++;//count times added by 1
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
        	//alert("scan button clicked");
			res=xmlhttp.responseText;
            arr=res.split("\n");
            res_epc=arr[2].replace(/\n/g,"");
            div_new.style.borderStyle="solid";
            div_new.style.borderColor="brown";
            div_new.style.cursor="pointer";
            //div_new.style.borderWidth="5px";
            var p1=document.createElement("p");
            p1.id="EPC";
            p1.innerHTML="EPC: "+res_epc;
            div_new.appendChild(p1);
            //div_new.click=read_tag;
            div_new.onclick=function()
            {
                read_tag(this);
             }
            div.appendChild(div_new);  //read the tag when this div element is clicked
		}
	}
	xmlhttp.open("GET","/cgi-bin/rfidks.exe?action=scan",true);
	//xmlhttp.open("GET","/reader.cpp",true);
    xmlhttp.send();
}

function clear()
{
    var div=document.getElementById("tag_body");
    var child_div=div.getElementsByTagName("div");
    for(var i=0;i<child_div.length;i++)
    {
        if(child_div[i].id!="title_bar")
        {
            div.removeChild(child_div[i]);
        }
     }
}

function read_tag(div)
{
	var xmlhttp = new XMLHttpRequest();
	var res,tid,epc;
    var child,i;
    child=div.getElementsByTagName("p");
    for(i=0;i<child.length;i++)
    {
        if(child[i].id=="EPC")
        {
            epc=child[i].innerHTML.replace("EPC: ","");
            break;
         }
     }

	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			res=xmlhttp.responseText.split("\n");
            var p=document.createElement("p");
            p.innerHTML="MAC: "+res[2];
            p.id="MAC";
            div.appendChild(p);

            div.onclick=function(){selected_div=div};
            //div.style.cursor="default";
            //
            selected_div=div;
		}
	}
	xmlhttp.open("GET","/cgi-bin/rfidks.exe?action=read&tag_epc="+epc,"true");
	xmlhttp.send();
}

function verify_tag()
{
	var mac;
	var res;
	var xmlhttp = new XMLHttpRequest();

    var child,i;
    child=selected_div.getElementsByTagName("p");
    for(i=0;i<child.length;i++)
    {
        if(child[i].id=="MAC")
        {
            mac=child[i].innerHTML.replace("MAC: ","");
            break;
         }
     }
    alert(mac);
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			res=xmlhttp.responseText;
            if(res=="FALSE")
            {
                selected_div.style.backgroundColor="red";
            }
			alert("This certificate is: "+res);
		}
	}
	xmlhttp.open("GET","/cgi-bin/rfidks.exe?action=verify&mac="+mac,"true");
	xmlhttp.send();
}

function create_verify_button()
{
    var button=document.createElement("button");
    button.id="verify";
    button.onclick=null;
    return button;
 }

$(document).ready(function()
		{
			//$("#scan").click(scan_tag);//alternative to onclick
            document.getElementById("scan").onclick=function()
            {
                scan_tag();
            }
            document.getElementById("clear").onclick=function(){clear();};
            document.getElementById("verify").onclick=function(){verify_tag()};
		});
