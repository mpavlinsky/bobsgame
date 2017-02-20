<?php 

header('Content-Type: text/plain');
$fh = fopen("version.txt", 'r');
$pageText = fread($fh, 25000);
echo $pageText;//nl2br($pageText);
fclose($fh);


$hit_count=0;
$statfile = @fopen("stats/count".date("Ymd").".txt","a+");
@rewind($statfile);
$hit_count = @fread($statfile, 25000);
$hit_count++;
@fclose($statfile);

$statfile = @fopen("stats/count".date("Ymd").".txt","w+");
@fwrite($statfile, $hit_count);
@fclose($statfile);
