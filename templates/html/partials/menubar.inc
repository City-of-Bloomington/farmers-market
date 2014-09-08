<?php
use Application\Models\Person;
?>
<nav>
	<?php

		$links = [
			'vendors' => 'vendor',
			'spaces'  => 'space',
			'people'  => 'person',
			'users'   => 'user'
		];
		$a = '<a href="%s">%s</a>';
		foreach ($links as $plural=>$single) {
			if (Person::isAllowed($plural, 'view')) {
				echo sprintf($a, BASE_URI.'/'.$plural, $this->translate([$single, $plural, 2]));
			}
		}
	?>
</nav>
