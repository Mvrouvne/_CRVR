<?php
session_start();

// Check if the user is already logged in, if yes, redirect to profile page
if (isset($_SESSION['username'])) {
    header("Location: profile.php");
    exit();
}

// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Check username and password (you should replace this with your own authentication logic)
    $username = "user";
    $password = "123";

    if ($_POST['username'] == $username && $_POST['password'] == $password) {
        // Authentication successful, set session variables
        $_SESSION['username'] = $username;
        header("Location: profile.php");
        exit();
    } else {
        $error = "Invalid username or password";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form method="POST" action="/login.php">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
    <?php if (isset($error)) echo "<p>$error</p>"; ?>
</body>
</html>