<?php
if (!defined('DATA_DIR')) { exit; }
header('Cache-control: no-cache');
header('Pragma: no-cache');
header('Content-Type: text/html; charset=EUC-JP');
/**
// XML������Ǥ���ɸ��⡼�ɤ���ʤ��ʤ�IE������
echo '<?xml version="1.0" encoding="EUC-JP"? >';
// ? > �����
/**/
?>

<?php if ($html_transitional) { ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja" lang="ja">
<?php } else { ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja">
<?php } ?>
<head>
 <meta http-equiv="content-type" content="application/xhtml+xml; charset=EUC-JP" />
 <meta http-equiv="content-style-type" content="text/css" />

<?php if (!$is_read) { ?>
 <meta name="robots" content="NOINDEX,NOFOLLOW" />
<?php } ?>

 <title><?php echo "$title - $page_title" ?></title>
 <link rel="stylesheet" href="../../website/skin/default.ja.css" type="text/css" media="screen" charset="Shift_JIS" />
 <link rel="stylesheet" href="../../website/skin/print.ja.css" type="text/css" media="print" charset="Shift_JIS" />
<?php
  global $trackback, $referer;
  if ($trackback) {
?>
 <meta http-equiv="Content-Script-Type" content="text/javascript" />
 <script type="text/javascript" src="skin/trackback.js"></script>
<?php } ?>
<?php echo $head_tag ?>
</head>
<body>

<div id="Header"><a href="http://mona.sourceforge.jp/"><img src="./img/MonaLogo.gif" width="320px" height="50px" alt="Mona OS �Υ�" title="Mona logo"></a></div>
<div id="Menu">
<?php if ($is_page) { ?>
<a href="<?php echo "$script?$r_page" ?>">�����</a> | 
<a href="<?php echo "$script?plugin=newpage&amp;refer=$r_page" ?>">����</a> | 
<a href="<?php echo $link_edit ?>">�Խ�</a> | 
<?php   if ($is_read and $function_freeze) { ?>
<?php     if ($is_freeze) { ?>
<a href="<?php echo $link_unfreeze ?>">�����</a> | 
<?php     } else { ?>
<a href="<?php echo $link_freeze ?>">���</a> | 
<?php     } ?>
<?php   } ?>
<a href="<?php echo $link_diff ?>">��ʬ</a> | 
<?php   if ((bool)ini_get('file_uploads')) { ?>
<a href="<?php echo $link_upload ?>">ź��</a> | 
<?php   }} ?>
<a href="<?php echo $link_top ?>">�ȥå�</a> | 
<a href="<?php echo $link_list ?>">����</a> | 
<?php if (arg_check('list')) { ?>
<a href="<?php echo $link_filelist ?>">�ե�����̾����</a> | 
<?php } ?>
<a href="<?php echo $link_search ?>">ñ�측��</a> | 
<a href="<?php echo $link_whatsnew ?>">�ǽ�����</a> | 
<?php if ($do_backup) { ?>
<a href="<?php echo $link_backup ?>">�Хå����å�</a> | 
<?php } ?>
<a href="<?php echo $link_help ?>">�إ��</a>
<?php
  if ($trackback) {
    $tb_id = tb_get_id($_page);
?>
 | <a href="<?php echo "$script?plugin=tb&amp;__mode=view&amp;tb_id=$tb_id" ?>">TrackBack(<?php echo tb_count($_page) ?>)</a>
<?php } ?>
<?php
  if ($referer) {
?>
 | <a href="<?php echo "$script?plugin=referer&amp;page=$r_page" ?>">��󥯸�</a>
<?php } ?>
</div>

<hr class="Start" title="�ʲ��Ϥ��Υڡ����Υ����ȥ�Ǥ�">

 <h1 id="title"><?php echo $page ?></h1>

<?php if ($is_page) { ?>
 <p class="PageLink"><a href="<?php echo "$script?$r_page" ?>"><?php echo "$script?$r_page" ?></a><p>
<?php } ?>

<p class="Attention"><strong>����Wiki�� <a href="http://wiki.monaos.org/">wiki.monaos.org</a> �ذ�ž���ޤ���</strong></p>
<p class="Attention"><strong>��õ���Υڡ�����<a href="http://wiki.monaos.org/pukiwiki.php?<?php print(urlencode($title)); ?>">������</a>���Ȼפ��ޤ�</strong></p>
<p class="Attention"><strong><small>�ʸ夳��Wiki��mona.sourceforge�ˤ��Խ����Ƥ��̣������ޤ���ΤǤ���մꤤ�ޤ���</small></strong></p>

<hr class="Start" title="�ʲ��Ϥ��Υڡ����Υᥤ�󥳥�ƥ�ĤǤ�">

<?php if (arg_check('read') and exist_plugin_convert('menu')) { ?>
<div id="Contents">
<div id="ContentsF"><?php echo $body ?></div>
<div id="Panels"><?php echo do_plugin_convert('menu') ?></div>
</div>
<?php } else { ?>
<div id="Contents"><?php echo $body ?></div>
<?php } ?>

<?php if ($notes) { ?>
<div id="note">
<?php echo $notes ?>
</div>
<?php } ?>


<?php if ($attaches) { ?>
<div id="attach">
<hr class="Start" title="�ʲ���ź�եե�����Ǥ�" />
<?php echo $attaches ?>
</div>
<?php } ?>

<hr class="Start" title="" />

<div id="toolbar">

<?php if ($is_page) { ?>
 <a href="<?php echo "$script?$r_page" ?>"><img src="./image/reload.png" width="20" height="20" alt="�����" title="�����" /></a>
 &nbsp;
 <a href="<?php echo $script ?>?plugin=newpage"><img src="./image/new.png" width="20" height="20" alt="����" title="����" /></a>
 <a href="<?php echo $link_edit ?>"><img src="./image/edit.png" width="20" height="20" alt="�Խ�" title="�Խ�" /></a>
 <a href="<?php echo $link_diff ?>"><img src="./image/diff.png" width="20" height="20" alt="��ʬ" title="��ʬ" /></a>
<?php   if ((bool)ini_get('file_uploads')) { ?>
 <a href="<?php echo $link_upload ?>"><img src="./image/file.png" width="20" height="20" alt="ź��" title="ź��" /></a>
<?php   } ?>
 &nbsp;
<?php } ?>
 <a href="<?php echo $link_top ?>"><img src="./image/top.png" width="20" height="20" alt="�ȥå�" title="�ȥå�" /></a>
 <a href="<?php echo $link_list ?>"><img src="./image/list.png" width="20" height="20" alt="����" title="����" /></a>
 <a href="<?php echo $link_search ?>"><img src="./image/search.png" width="20" height="20" alt="����" title="����" /></a>
 <a href="<?php echo $link_whatsnew ?>"><img src="./image/recentchanges.png" width="20" height="20" alt="�ǽ�����" title="�ǽ�����" /></a>
<?php if ($do_backup) { ?>
 <a href="<?php echo $link_backup ?>"><img src="./image/backup.png" width="20" height="20" alt="�Хå����å�" title="�Хå����å�" /></a>
<?php } ?>
 &nbsp;
 <a href="<?php echo $link_help ?>"><img src="./image/help.png" width="20" height="20" alt="�إ��" title="�إ��" /></a>
 &nbsp;
 <a href="<?php echo $link_rss ?>"><img src="./image/rss.png" width="36" height="14" alt="�ǽ�������RSS" title="�ǽ�������RSS" /></a>
</div>

<hr class="Start" title="�ʲ��Ϥ��Υڡ����˴ؤ��뤤���Ĥ��ξ���Ǥ�">

<div id="modify">
<?php if ($lastmodified) { ?>
Last-modified: <?php echo $lastmodified ?>;&nbsp;
<?php } ?>
Modified by <a href="<?php echo $modifierlink ?>"><?php echo $modifier ?></a>
</div>
<?php if ($related) { ?>
<div id="related">Link: <?php echo $related ?></div>
<?php } ?>
<div id="versioninfo"><?php echo S_COPYRIGHT ?><br />Powered by PHP <?php echo PHP_VERSION ?></div>
<div id="converttime">HTML convert time to <?php echo $taketime ?> sec.</div>

<hr class="Start" title="�ʲ������ɽ���Ǥ�">

<div id="LinkSF"><a href="http://sourceforge.jp"><img src="http://sourceforge.jp/sflogo.php?group_id=320" width="96px" height="31px" alt="SourceForge�ؤΥ��" title="MonaOS��SourceFORGE.jp���󶡤Ǳ��Ĥ��Ƥ���ޤ�"></a></div>
<div id="Copyright">Copyright(C)2003-2005 MonaProjectTeam, all rights reserved. powered by www.be-interactive.org</div>

</body>
</html>
