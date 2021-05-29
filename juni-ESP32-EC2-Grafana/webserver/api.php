<?php
$_INCLUDED = true;

include("mysql_connect.php");

$temp = $_GET["temp"];
	
// prepare and bind
$stmt = $conn->prepare("INSERT INTO <TABLENAME> (Temperature) VALUES (?)");
$stmt->bind_param("s",$temp);

$stmt->execute() or die($stmt->error);	


?>