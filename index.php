<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="5" >
    <link rel="stylesheet" type="text/css" href="style.css" media="screen"/>

	<title> Sensor Hujan </title>

</head>

<body>

    <h1>SENSOR HUJAN</h1>
<?php
$servername = "server1.komputasi.org";
$username = "komputas_komputas";
$password = "XO0zgRvZVX";
$dbname = "komputas_jemurancerdas";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, sensor, value1, reading_time, statushujan FROM sensordata ORDER BY id DESC"; /*select items to display from the sensordata table in the data base*/

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <th>ID</th> 
        <th>Date / Time</th> 
        <th>Sensor</th> 
        <th>Output Sensor</th>
        <th>Status Hujan</th>   
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_reading_time = $row["reading_time"];
        $row_sensor = $row["sensor"];
        $row_value1 = $row["value1"];
        $row_statushujan = $row["statushujan"];
        
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
       // $row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_reading_time . '</td> 
                <td>' . $row_sensor . '</td> 
                <td>' . $row_value1 . '</td> 
                <td>' . $row_statushujan . '</td> 
                
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>

</body>
</html>

	</body>
</html>