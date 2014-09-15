<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php
	$this->layout = 'full-width';
	$this->_include('partials/header.inc');
?>
<body>
	<div id="panel-container">
		<div id="content-panel">
			<?php
				include BLOSSOM.'/errorMessages.php';

				echo $this->includeBlocks();
			?>
		</div>
	</div>
</body>
</html>
<?php
	$this->_include('partials/garbageCollection.inc');
?>
