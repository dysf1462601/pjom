<?php
ini_set('memory_limit', '-1');
// ini_set('memory_limit','512M');

// $br = (php_sapi_name() == "cli")? "":"<br>";

// if(!extension_loaded('pjom')) {
// 	dl('pjom.' . PHP_SHLIB_SUFFIX);
// }
// $module = 'pjom';
// $functions = get_extension_funcs($module);
// echo "Functions available in the test extension:$br\n";
// foreach($functions as $func) {
//     echo $func."$br\n";
// }
// echo "$br\n";
// $function = 'confirm_' . $module . '_compiled';
// if (extension_loaded($module)) {
// 	$str = $function($module);
// } else {
// 	$str = "Module $module is not compiled into PHP";
// }
// echo "$str\n";

// echo pom_pjom("sb","","");

$DATA['method'] = "getName";
$DATA['parms']['name'] = 'pom';

$jarPathStr = "/root/download/php-5.6.23/ext/pjom/tests/java/test.jar"; // : 分割
$className  = "com/test/MyTest";



$ret = json_decode(pom_pjom(json_encode($DATA),$jarPathStr,$className),true);

var_dump($ret);

?>
