#!/usr/bin/env php
<?php
#==============================================================================
#  Copyright 2016 Frog Chen
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#==============================================================================
# ■ additional-comments.php
#------------------------------------------------------------------------------
#   额外的注释。通常是塞不进其它代码中才放到这个文件里来的。
#   关于在一个C++项目中使用PHP的理由……
#==============================================================================

echo "PHP是世界上最好的语言！\n";

function chapter0() { // 第零章：关于本文件
	# 　　本章说明这个文件的主要目的。作为additional comments，其作用之一当然是
	# 写注释，但是其还有这些功能：
	# 　　◦ 介绍
	#     ◦ 提示
	# 　　◦ 画图
	# 　　◦ 刷文档提交数
	# 　　◦ 刷差异增减行数
	#     ◦ 其它我也不知道的用处
	return NULL;
}

function chapter1() { // 第一章：历史
	# 　　从Initial commit给出的信息来看，本项目创建于2016年1月18日星期一
	# 17:47:59 CST（不是UTC。当时我这的电脑时区问题还没调好）。
	# 　　关于本仓库的历史，执行git show 500cedd1a8303ea5620b60c35b5fdb659a25d99b
	# 就可以看到我在建立新仓库之初所感所想，因此不再在这里重复说明。基本概况
	# 可参考下面这张大致的分支图：
	#
	#    satgo1546: [frogimine]                 [frogimine]-⋯ ← 你在这里
	#                           \               /
	#    IcebergOS:             [frogimine]-[iViK]-[Cryst]-⋯
	#
	# 　　额外说明：从iViK到（新）frogimine仓库中间并不是保留历史的分支，而是我从
	# iViK的某些提交中抽取代码新建的一个仓库——与原仓库没有直接关系。但是在
	# 2016年9月，我把玩了一下Git后实验性地把原始仓库中的一些提交移过来了，不知
	# 有没有什么副作用。不过这也只是重写了一遍历史罢了，在Git的世界中历史总是被
	# 不断重写的。
	# 　　额外说明二：考古研究队可以从av7，哦不，frogimine-the-old-days标签开始，
	# 一直追溯到Initial commit。如果谁有那个兴趣的话。你可能需要常备地图和GPS：
	# git log --decorate --oneline --graph走你。最好为此命令设置一个别名，比如我
	# 设了git graph，也许gr会方便很多。
	# 　　额外说明三：本项目的提交历史消息十分丰富（可能也存在滑稽：详见
	# IcebergOS/VM-76仓库中的BulletinBoard.md中的“这些提交消息十分滑稽”一节）。
	# 这个库也并不是代码库，而是文档库——虽然写得并不怎么好。#(滑稽)
	# 　　额外说明四：分裂是2016年1月26日执行的，才过一星期就一言不合了。
	return "History";
}

?>
