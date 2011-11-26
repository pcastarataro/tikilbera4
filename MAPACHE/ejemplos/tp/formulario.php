<html>
<body>
<form action="pr.cgi" method="post" enctype="multipart/form-data"><br>
<?php
$shortopts  = "";
$longopts  = array(
    "cantArchivos:",     // Valor obligatorio - invocar desde consola asi: php test.php --cantArchivos 2
);
$options = getopt($shortopts, $longopts);
for ($i=1; $i<=$options["cantArchivos"]; $i++)
  {    
    echo "<form method=\"post\" enctype=\"multipart/form-data\"><br>\n";
    echo "<label for=\"file\"]>Archivo </label>\n";
    echo $i;
    echo "<input type=file size=60 name=\"file\"><br>\n";
  }
?>
<input type=submit value=">>"><br>
</form><br>
</body>
</html> 