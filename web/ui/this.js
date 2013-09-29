window.onload=function()
{//prevent getElementById from returning null
	var p=document.getElementById("p1");
	p.onclick=changecolor;
	document.getElementById("p2").onclick=changebackground;
}

function changediv(div)
{
	document.getElementById("p2").style.font="italic bold 20px arial,serif";
	alert(div.id);
}

function changetext(id)
{
	id.innerHTML="Ooops!Text has been changed.";
}

function changecolor()
{
	if(!this)
		return;
	this.style.color="green";
}

function changebackground()
{
	this.style.color="#B0C4DE";
	this.style.textDecoration="overline";
	this.style.backgroundColor="brown";
}
