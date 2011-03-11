<?php
// $Id$

/**
 * @file character-sheet.tpl.php
 * This file is the template for the character sheet of each individual character in a node.
 * 
 * Available variables:
 * $char_id: A string with an id for this character.
 * $chartitle: A string with the character's name, and any prefix or suffix, like "Sergeant Major" 
 *             or "Hand of A'Dal". Linked to wowarmory.com.
 * $guild: A string with the guildname, if the character is a member of a guild. Linked to 
 *         guild-profile if it is registered at this site. Also an external link to wowarmory.com.
 * $infostring: A string containing level, class, servername and region.
 * $prof0: A string with the first profession and its level.
 * $prof1: A string with the second profession and its level.
 * $class_class: A string with the character's class, prepared for output in the class attribute.
 * $faction_class: A string with the character's faction, prepared for output in the class attribute.
 * $race_class: A string with the character's race, prepared for output in the class attribute.
 * $prof0_style: An array with the following elements:
 * - 'class': A string with info about the first profession, prepared for output in the class attribute.
 * - 'percent': An integer, representing the percentage of this skill this character has (of 450 max).
 * $prof1_style: An array with the following elements:
 * - 'class': A string with info about the second profession, prepared for output in the class attribute.
 * - 'percent': An integer, representing the percentage of this skill this character has (of 450 max).
 * 
 * @see characters.module, line 240, 322.
 */
?>
<div id="<?php print $char_id; ?>" class="characters-character-sheet <?php print $class_class . ' ' . $faction_class . ' ' . $race_class; ?>">
  <h3 class="characters-charname"><?php print $chartitle; ?></h3>

  <?php if (!empty($guild)) : ?>
  <p class="characters-character-guild"><?php print $guild; ?></p>
  <?php endif; ?>
  <p class="characters-character-info"><?php print $infostring; ?></p>

  <?php if (!empty($prof0)) : ?>
  <p class="characters-character-prof <?php print $prof0_style['class']; ?>">
    <?php print $prof0; ?>
  </p>
  <?php endif; ?>
  <?php if (!empty($prof1)) : ?>
  <p class="characters-character-prof <?php print $prof0_style['class']; ?>">
    <?php print $prof1; ?>
  </p>
  <?php endif; ?>
</div><!-- /.characters-character-sheet #<?php print $char_id; ?> -->
