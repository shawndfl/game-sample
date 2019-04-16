<html>
<head>
<title>PHP Test</title>
</head>
<body>
<?php

function getFile($url)
{
    echo '<p>init curl</p><br>';
    $value = file_get_contents($url);
    echo $value;
}

function runCurl($url)
{
    $ch = curl_init();

    // set url
    curl_setopt($ch, CURLOPT_URL, $url);

    // return the transfer as a string
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

    // $output contains the output string
    $output = curl_exec($ch);

    echo $output;
    
    // close curl resource to free up system resources
    curl_close($ch);
}
?>
 <?php runCurl("http://localhost:8080/testing?testing=1&x=2"); ?> 
 </body>
</html>