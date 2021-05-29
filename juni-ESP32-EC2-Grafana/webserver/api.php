<?php
$_INCLUDED = true;

include("mysql_connect.php");

if(!isset($_GET["temp"])){echo "No temp get value set";}
else{
	$temp = $_GET["temp"];
		
	// prepare and bind
	$stmt = $conn->prepare("INSERT INTO <TABLENAME> (Temperature) VALUES (?)");
	$stmt->bind_param("s",$temp);

	$stmt->execute() or die($stmt->error);	

	echo "insert successful!";
}
?>