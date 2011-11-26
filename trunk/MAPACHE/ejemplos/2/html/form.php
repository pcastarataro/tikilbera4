<html>
<head>
<title>Ejemplo 2 - Formulario php</title>
</head>
<body>
<div style="text-align: center">
<h1>Mapache</h1>
<h3>Ejemplo 2 - Formulario php</h3>
<?php
$shortopts  = "";
$longopts  = array(
    "nombre:",     // Valor obligatorio - invocar desde consola asi: php test.php --cantArchivos 2
);
$options = getopt($shortopts, $longopts);
echo "Su nombre es: ";
echo $options["nombre"];
?>
</div>
</body>
</html> 