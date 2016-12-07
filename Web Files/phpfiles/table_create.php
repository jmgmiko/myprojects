<?php
    $host ="localhost";
    $username="root";
    $password="root";
    $database="airlines";
    $sql=mysqli_connect($host, $username, $password, $database);
    if ($sql) {
        $comm="SELECT * from list";
       $result=mysqli_query($sql, $comm);
       while ($row=mysqli_fetch_assoc($result)) {
           echo "<tr>";
               echo "<td>" .$row["Name"]. "</td>";
               echo "<td>" .$row["Country"]. "</td>";
               echo "<td>" .$row["Alliance"]. "</td>";
           echo "</tr>";
       }
    }
    mysqli_close($sql);
?>