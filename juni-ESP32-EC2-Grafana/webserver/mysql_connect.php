<?php
if(!isset($_INCLUDED)){die("ERROR");}

$servername = "localhost";

$username = "<USERNAME>";
$password = "<PASSWORD>";

$database = "<DATABASENAME>";


// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

?>