<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<link rel="stylesheet" href="css/bootstrap.css">
		<link rel="stylesheet" href="CSS Files/style.css">
	</head>
	<body>
		<div class="container-fluid">
			<div class="row">
				<div class="col-sm-10 col-xs-12 col-sm-offset-1 text-center">
					<?php
						$name=$_GET['name'];
						$origin=$_GET['country'];
						echo "<h1 class='hidden-lg'>Hello, ".$name." of ".$origin.". Remember me?</h1>";
					?>
					<div class="visible-lg">
						<img src="img/Tulips.jpg" class="img-circle">
						<h1>It is I, Miko Gaid!!!</h1>
					</div>
				</div>
			</div>
		</div>
	</body>
</html>