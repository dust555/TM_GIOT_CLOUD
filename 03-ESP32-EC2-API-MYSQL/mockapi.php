<?php
$_INCLUDED = true;

include("mysql_connect.php");


$device_id = "devid";
$temp = rand (21,22);
$humid = rand(60,70);

// prepare and bind
$stmt = $conn->prepare("INSERT INTO esp32 (device_id, temperature, humidity) VALUES (?, ?, ?)");
$stmt->bind_param("sss", $device_id, $temp, $humid);

$stmt->execute();

file_put_contents('error.txt', $stmt->error);

echo "Temp: ".$temp.", Humid: ".$humid;

?>
