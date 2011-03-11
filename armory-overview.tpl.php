<?php
// $Id$

/**
 * @file armory-overview.tpl.php
 * Template file for the armory overview page, listing guilds, characters and other statistics.
 * 
 * Available variables:
 * - $intro: Intro text to the Armory (this can be changed at admin/settings/armory).
 * - $tabs: Tabs as <ul> for tabbed interface.
 * - $guilds: Themed output of all guilds in the database.
 * - $characters: Themed output of all characters in the database.
 * - $meta: Additional information about the "site armory".
 */
?>
<div id="armory-overview">
  <div id="armory-overview-intro">
    <p><?php print $intro; ?></p>
  </div>
  <div id="armory-overview-tabs">
    <?php print $tabs; ?>
    <div id="armory-overview-guilds">
      <?php print $guilds; ?>
    </div>
    <div id="armory-overview-characters">
      <?php print $characters; ?>
    </div>
  </div>
  <div id="armory-overview-meta">
    <?php print $meta; ?>
  </div>
</div>