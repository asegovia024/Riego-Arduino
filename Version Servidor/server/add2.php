<?php
   	include("connect.php");
   	
   	$link=Connection();

	//$temp1=$_POST["temp1"];
	$hum1=$_GET['hum1'];
   $temp1 =$_GET['temp1'];
//$numero=count ($_GET);
//$tags = array_keys($_GET);
//$valores =array_values($_GET);
   
//$temp1=htmlspecialchars($_GET['valores']);
//echo $_GET['temp1'];
//$temp1=$valores[0];

	/*$query = "INSERT INTO `tempLog` (`temperature`, `humidity`) 
		VALUES ('".$temp1."','".$hum1."')"; */

$query = "INSERT INTO `databaseia`.`templog` (`timeStamp`, `temperature`, `humidity`) VALUES (NOW(), '".$temp1."', '".$hum1."')";

   	
   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
