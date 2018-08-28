<?php

require_once 'telnet.class.php';

$status = '';
$telnet = new Telnet();


if(!$telnet->connect())
{
    echo "failed to connect";
}
if($_SERVER["REQUEST_METHOD"] == "POST")
{
    if(isset($_POST["on"]))
    {
        $telnet->exec('on');
        $status = "its ON";


    }
    if(isset($_POST["off"]))
    {
        $telnet->exec('off');
        $status = "its OFF";

    }
}

?>
<div id="controlshit">
    <form action="test.php" method="post">
        <div>
            <input type="submit" value="on" name="on">
        </div>
        <div>
            <input type="submit" value="off" name="off">
        </div>
    </form>
    <div id="status">

        <p><?php echo $status; ?></p>
    </div>
</div>