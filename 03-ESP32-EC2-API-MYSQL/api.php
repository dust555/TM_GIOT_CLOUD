<?php
$_INCLUDED = true;

include("mysql_connect.php");

$headers = getallheaders();
	
// prepare and bind
$stmt = $conn->prepare("INSERT INTO esp32 (device_id, temperature, humidity) VALUES (?, ?, ?)");
$stmt->bind_param("sss", $headers["device_id"], $headers["temperature"], $headers["humidity"]);

$stmt->execute();	

	
	
    file_put_contents('error.txt', $stmt->error);




?>