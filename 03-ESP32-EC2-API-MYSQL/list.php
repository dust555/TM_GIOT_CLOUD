<?php
$_INCLUDED = true;

include("mysql_connect.php");


$sql = "SELECT * FROM esp32 ORDER BY Datetime DESC";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
    echo $row["Datetime"].": device_id: " . $row["Device_id"]. " - Temperature: " . $row["Temperature"]. " - Humidity: " . $row["Humidity"]. "<br>";
  }
} else {
  echo "0 results";
}

?>