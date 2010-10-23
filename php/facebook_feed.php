<?php
require 'facebook.php';

$facebook = new Facebook(array(
	'appId'  => "consumerKey",
	'secret' => "consumerSecret",
	'cookie' => true
));

$me = null;
$session = $facebook->getSession();
if ($session) {
	try {
		$me = $facebook->api('/me');
	} catch (Exception $e) {
	}
}
if (!$me) {
	$url = $facebook->getLoginUrl(array('req_perms' => 'publish_stream'));
	header("Location: " . $url);
	exit;
}
$paramAry = array(
	'method' => 'stream.publish',
	'message' => 'こんにちは、世界',
	'action_links' => array(array(
		'text' => 'ユニークビジョン',
		'href' => 'http://www.uniquevision.co.jp/'))
);
try {
	$response = $facebook->api($paramAry);
	echo $response;
} catch (Exception $e) {
	throw $e;
}