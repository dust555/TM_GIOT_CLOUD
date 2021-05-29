<?php
$_INCLUDED = true;

include("mysql_connect.php");


$sql = "SELECT * FROM <TABLENAME> ORDER BY Datetime DESC";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
    echo $row["Datetime"].": Temperature: " . $row["Temperature"]. "<br>";
  }
} else {
  echo "0 results";
}

?>