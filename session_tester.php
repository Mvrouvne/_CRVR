<?php
// Start the session
session_start();

// Set session variables
$_SESSION["test_session"] = "Hello, this is a test session variable!";

// Display session variable value
echo "Session variable 'test_session' is set!<br>";
echo "Value is: " . $_SESSION["test_session"];
?>
