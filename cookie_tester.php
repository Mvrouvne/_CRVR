<?php
// Set a cookie
setcookie("test_cookie", "Hello, this is a test cookie!", time() + 3600, "/");  // cookie will expire in 1 hour

// Check if the cookie is set and display its value
if(isset($_COOKIE["test_cookie"])) {
    echo "Cookie 'test_cookie' is set!<br>";
    echo "Value is: " . $_COOKIE["test_cookie"];
} else {
    echo "Cookie 'test_cookie' is not set!";
}
?>
