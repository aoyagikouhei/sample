function makeTwitterDate(src) {
	src.match(/(\d\d\d\d)-(\d\d)-(\d\d) (\d\d):(\d\d):(\d\d)/);
	date = new Date(RegExp.$1, Number(RegExp.$2) - 1, RegExp.$3
			, RegExp.$4, RegExp.$5, RegExp.$6);
	now = new Date();
	diff = now.getTime() - date.getTime();
	if (diff < 1000 * 60) {
		return Math.round(diff / 1000) + "秒前";
	} else if (diff < 1000 * 60 * 60) {
		return Math.round(diff / (1000 * 60)) + "分前";
	} else if (diff < 1000 * 60 * 60 * 24) {
		return "約" + Math.round(diff / (1000 * 60 * 60)) + "時間前";
	} else {
		var monthAry = ['Jan', 'Feb', 'Mar', 'Apl', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
		var hour = date.getHours();
		var ampm = " AM ";
		if (hour > 12) {
			hour = hour - 12;
			ampm = " PM ";
		}
		var minute = String(date.getMinutes());
		if (minute.length == 1) {
			minute = "0" + minute;
		}
		var day = date.getDate();
		var prefix = "th";
		switch (day) {
		case 1 :
		case 21 :
		case 31 :
			prefix = "st";
			break;
		case 2 :
		case 22 :
			prefix = "nd";
			break;
		case 3 :
		case 23 :
			prefix = "rd";
			break;
		}
		var year = "";
		if (now.getFullYear() != date.getFullYear()) {
			year = ", " + String(date.getFullYear());
		}
		return String(hour) + ":" + minute + ampm
			+ monthAry[date.getMonth()] + ' ' 
			+ String(day) + prefix + year;
	}
}
