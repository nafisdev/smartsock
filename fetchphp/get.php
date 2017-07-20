<?php
$servername = "localhost";
$username = "vehi";
$password = "4VphoSqROLlaMwqb";
$dbname = "vehicom";
$now = new DateTime();

$conn = mysqli_connect("localhost","root","");
if (!$conn)
{
    die('Could not connect: ' . mysqli_error($conn));
}
$con_result = mysqli_select_db($conn,"vehicom");
if(!$con_result)
{
	die('Could not connect to specific database: ' . mysqli_error($conn));	
}
	
$sql1 = "SELECT status FROM devicetable WHERE did=1234";
$result1 = $conn->query($sql1);

if ($result1->num_rows > 0) {
    // output data of each row
    while($row = $result1->fetch_assoc()) {
        echo $row["status"];
    }
} else {
    echo "0 results";
}
	
	mysqli_close($conn);
?>
</html>