<?php
$servername = "localhost";
$username = "root"; // Ganti dengan username MySQL Anda
$password = ""; // Ganti dengan password MySQL Anda
$dbname = "sensor_data"; // Ganti dengan nama database Anda

// Membuat koneksi ke database MySQL
$conn = new mysqli($servername, $username, $password, $dbname);

// Mengecek koneksi
if ($conn->connect_error) {
  die("Koneksi ke database gagal: " . $conn->connect_error);
}

// Menerima data dari permintaan POST
$data = json_decode(file_get_contents("php://input"), true);

if(isset($data['rainValue'])) {
    $rainValue = $data['rainValue'];

    // Menyimpan data ke database
    $sql = "INSERT INTO sensor_data (rain_value, timestamp) VALUES ('$rainValue', NOW())";

    if ($conn->query($sql) === TRUE) {
        echo "Data sensor berhasil disimpan";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    echo "Data sensor tidak valid";
}

$conn->close();
?>
