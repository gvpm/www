<?php
if(isset($_POST['field1']) && isset($_POST['field2'])) {
    date_default_timezone_set('Europe/London');
    $date = date('H:i:s');
    $data = $date . ' - ' . $_POST['field1'] . ' - ' . $_POST['field2'] . "\n";
    
    $restaurant = $_POST['field1'];
    $guests = $_POST['field2']; 
    $ret = file_put_contents('data.txt', $data, FILE_APPEND | LOCK_EX);
    if($ret === false) {
        die('There was an error writing this file');
    }
    else {
        //echo "$restaurant";
	//echo "$guests guests";
    }
}
else {
   die('No data, go to lureparty.co.uk/deals');
}
?>
<html>
<title>LureParty - SCREENSHOT THIS SCREEN</title>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

   

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/business-frontpage.css" rel="stylesheet">
    <link href="css/custom.css" rel="stylesheet">


</head>

<body>
<script>
  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','https://www.google-analytics.com/analytics.js','ga');

  ga('create', 'UA-83593341-1', 'auto');
  ga('send', 'pageview');

</script>
<header>
 <div class="row">
                <div class="col-md-4 col-md-offset-4">
		<!--<h4>   Screenshot this and show at the restaurant   <h4>-->
                <img class="img-responsive img-center" src="img/top.png" alt="">

</header>
<h3 class="text-center">
<?php
if(isset($_POST['field1']) && isset($_POST['field2'])) {
    $restaurant = $_POST['field1'];
    echo "$restaurant";
}
else {
   die('No data, go to lureparty.co.uk/deals');
}
?>
<h3>
<h4 class="text-center">
<?php
if(isset($_POST['field1']) && isset($_POST['field2'])) {
    $guests = $_POST['field2'];
    echo "Nº of guests: $guests";
}
else {
   die('No data, go to lureparty.co.uk/deals');
}
?>
<h4>
<h4 class="text-center">
<?php

echo "Code: ";
echo rand(100000,999999);
?>
<h4>
<img class="img-responsive img-center" src="img/down.png" alt="">

                </div>
           
        </div>

 <div class="row">
            <div class="col-md-4 col-md-offset-4" style="text-align: center">

             <a href="deals.html" class="btn btn-default">Back to Deals</a>

                <p></p>
            </div>           
        </div>

</body>

