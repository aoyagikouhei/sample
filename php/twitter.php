public function makeTwitterDate($src) {
	$date = new DateTime($src);
	$now = new DateTime();
	$diff = $date->diff($now, true);
	if ($diff->y > 0) {
		return $date->format("g:i A M jS, Y");
	}
	if ($diff->d > 0) {
		return $date->format("g:i A M jS");
	}
	if ($diff->h > 0) {
		return "約" . $diff->h . "時間前";
	}
	if ($diff->m > 0) {
		return $diff->m . "分前";		
	}
	return $diff->s . "秒前";
}
