<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Test Page for Apache Installation</title>
</head>
<!-- Background white, links blue (unvisited), navy (visited), red
(active) -->
<body bgcolor="#FFFFFF" text="#000000" link="#0000FF" vlink="#000080" alink="#FF0000">

	<?php 
		require_once(dirname(__FILE__) . '/' . "RegSoftPAK.php");

		$NewPak = new Pak();
//		$NewPak->IssueTime = mktime(12,13,14,1,2,2002);
//		$NewPak->IssueTime = mktime(12,13,14,1,1,2002);
		$NewPak->IssueChannel = 12;
		$NewPak->Duration = 30;
		$NewPak->Users = 9;
		$NewPak->ProductLevelUpgrade = 2;
		$NewPak->ProductLevel = 3;
		$NewPak->ProductVersionUpgrade = 200;
		$NewPak->ProductVersion = 300;
		$NewPak->Component[4] = true;
		$NewPak->dbg_Print();
		echo "<br/> Pak->get_Code() = " . $NewPak->get_Code();
		$NewPak->dbg_Print();
		echo "<br/> Pak->get_Code() = " . $NewPak->get_Code();
		$Pak = $NewPak->get_Code();
		echo "<br/> Pak->put_Code($Pak, '', '') = " . ($NewPak->put_Code($Pak, "", "")?"1":"0");
		$Pak = substr($Pak, 0, 28) . "A";
		echo "<br/> Pak->put_Code($Pak, '', '') = " . ($NewPak->put_Code($Pak, "", "")?"1":"0");
		echo "<br/>";

		echo "<br/> Pak1Autoweb0102Generate('terry@pothecary.com') = " . Pak1Autoweb0102Generate("terry@pothecary.com");
		echo "<br/> Pak1Autoweb0102Generate('terry@pothecary.com1') = " . Pak1Autoweb0102Generate("terry@pothecary.com1");

		$NewPak->put_Code(Pak1Autoweb0102Generate("terry@pothecary.com"), "Autoweb", "terry@pothecary.com");
		$NewPak->dbg_Print();
	?>

	<br/>


</body>
</html>

