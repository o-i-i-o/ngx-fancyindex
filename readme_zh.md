# Nginx Fancy Index 模块

[![Build Status](https://travis-ci.com/aperezdc/ngx-fancyindex.svg?branch=master)](https://travis-ci.com/aperezdc/ngx-fancyindex)

## 目录

- [环境要求](#环境要求)
- [构建](#构建)
- [示例](#示例)
- [指令](#指令)

Fancy Index 模块可以生成文件列表，效果与内置的
[autoindex](http://wiki.nginx.org/NginxHttpAutoindexModule) 模块类似，但增加了一些样式能力。
之所以能做到这一点，是因为该模块允许对生成的内容进行一定程度的定制：

- 自定义页眉，可放在本地或远程。
- 自定义页脚，可放在本地或远程。
- 添加自定义 CSS 样式规则。
- 可以选择按名称（默认）、修改时间或大小排序，并且支持升序（默认）或降序。

本模块面向 [Nginx](https://nginx.org)，这是一个由
[Igor Sysoev](http://sysoev.ru) 编写的高性能开源 Web 服务器。

## 环境要求

### CentOS、RHEL、Fedora Linux

使用 [官方稳定版](https://www.nginx.com/resources/wiki/start/topics/tutorials/install/)
Nginx 仓库的用户，可以使用
[动态模块附加软件包仓库](https://www.getpagespeed.com/redhat)，其中已经包含 fancyindex。

先安装仓库配置，然后安装模块包：

```shell
yum -y install https://extras.getpagespeed.com/release-latest.rpm
yum -y install nginx-module-fancyindex
```

然后在 `/etc/nginx/nginx.conf` 中加载模块：

```nginx
load_module "modules/ngx_http_fancyindex_module.so";
```

### macOS

用户可以通过 MacPorts
[在 macOS 上安装 Nginx](https://ports.macports.org/port/nginx)，其中已经包含 fancyindex：

```shell
sudo port install nginx
```

### 其他平台

在大多数其他情况下，你需要 Nginx 的源码。从 0.8 系列开始的所有版本都应该可用。

如果要使用 `fancyindex_header_` 和 `fancyindex_footer_` 指令，还需要 Nginx
内置了
[ngx_http_addition_module](https://nginx.org/en/docs/http/ngx_http_addition_module.html)。

## 构建

1. 解压 Nginx 源码：

   ```shell
   $ gunzip -c nginx-?.?.?.tar.gz | tar -xvf -
   ```

2. 解压 fancy index 模块源码：

   ```shell
   $ gunzip -c nginx-fancyindex-?.?.?.tar.gz | tar -xvf -
   ```

3. 进入包含 Nginx 源码的目录，带所需选项运行配置脚本，并确保使用
   `--add-module` 参数指向包含 fancy index 模块源码的目录：

   ```shell
   $ cd nginx-?.?.?
   $ ./configure --add-module=../nginx-fancyindex-?.?.? \
      [--with-http_addition_module] [其他所需选项]
   ```

   从 0.4.0 版本开始，模块也可以构建为
   [动态模块](https://www.nginx.com/resources/wiki/extending/converting/)：
   使用 `--add-dynamic-module=…` 代替 `--add-module=…`，并在配置文件中加入
   `load_module "modules/ngx_http_fancyindex_module.so";`。

4. 构建并安装：

   ```shell
   $ make
   ```

   然后以 `root` 身份执行：

   ```shell
   # make install
   ```

5. 使用模块的[指令](#指令)配置 Nginx。

## 示例

可以在 Nginx 配置文件的 `server` 段中加入以下内容，测试默认的内置样式：

```nginx
location / {
  fancyindex on;              # 启用 fancy index。
  fancyindex_exact_size off;  # 输出人类可读的文件大小。
}
```

### 主题

以下主题展示了使用本模块可以达到的定制程度：

- [@TheInsomniac](https://github.com/TheInsomniac) 的
  [主题](https://github.com/TheInsomniac/Nginx-Fancyindex-Theme)。使用自定义页眉和页脚。
- [@Naereen](https://github.com/Naereen/) 的
  [主题](https://github.com/Naereen/Nginx-Fancyindex-Theme)。使用自定义页眉和页脚，
  页眉中包含一个搜索框，可用 JavaScript 按文件名过滤。
- [@fraoustin](https://github.com/fraoustin) 的
  [主题](https://github.com/fraoustin/Nginx-Fancyindex-Theme)。使用 Material Design
  元素的自适应主题。
- [@alehaa](https://github.com/alehaa) 的
  [主题](https://github.com/alehaa/nginx-fancyindex-flat-theme)。基于 Bootstrap 4 和
  FontAwesome 的简洁扁平主题。

## 指令

### fancyindex

**语法：** `fancyindex [on | off]`  
**默认值：** `fancyindex off`  
**上下文：** `http`、`server`、`location`  
**描述：** 启用或禁用 fancy 目录索引。

### fancyindex_default_sort

**语法：** `fancyindex_default_sort [name | size | date | name_desc | size_desc | date_desc]`  
**默认值：** `fancyindex_default_sort name`  
**上下文：** `http`、`server`、`location`  
**描述：** 设置默认的排序方式。

### fancyindex_case_sensitive

**语法：** `fancyindex_case_sensitive [on | off]`  
**默认值：** `fancyindex_case_sensitive on`  
**上下文：** `http`、`server`、`location`  
**描述：** 启用（默认）时，按名称排序区分大小写；禁用时，按名称排序忽略大小写。

### fancyindex_directories_first

**语法：** `fancyindex_directories_first [on | off]`  
**默认值：** `fancyindex_directories_first on`  
**上下文：** `http`、`server`、`location`  
**描述：** 启用（默认）时，将目录归为一组，并排在所有普通文件之前；禁用时，目录与文件一起排序。

### fancyindex_css_href

**语法：** `fancyindex_css_href uri`  
**默认值：** `fancyindex_css_href ""`  
**上下文：** `http`、`server`、`location`  
**描述：** 允许在生成的列表中插入指向 CSS 样式表的链接。提供的 `uri` 参数会原样插入
`<link>` HTML 标签。该链接插入在内置 CSS 规则之后，因此你可以覆盖默认样式。

### fancyindex_exact_size

**语法：** `fancyindex_exact_size [on | off]`  
**默认值：** `fancyindex_exact_size on`  
**上下文：** `http`、`server`、`location`  
**描述：** 定义目录列表中文件大小的表示方式：精确显示，或者四舍五入到千字节、兆字节和吉字节。

### fancyindex_footer

**语法：** `fancyindex_footer path [subrequest | local]`  
**默认值：** `fancyindex_footer ""`  
**上下文：** `http`、`server`、`location`  
**描述：** 指定插入到目录列表底部的文件。如果设置为空字符串，则发送模块提供的默认页脚。
可选参数指明 `path` 是作为 URI 通过子请求加载（默认），还是指向本地文件。

> **注意：** 使用该指令需要 Nginx 内置了 ngx_http_addition_module。

> **警告：** 插入自定义页眉/页脚时会发出子请求，因此原则上任何 URL 都可以作为它们的来源。
> 虽然外部 URL 也能工作，但只支持使用内部 URL。外部 URL 完全没有经过测试，使用它们会让
> Nginx 在等待子请求完成时阻塞。如果你确实需要外部页眉/页脚，请
> [告诉我](mailto:aperez@igalia.com)。

### fancyindex_header

**语法：** `fancyindex_header path [subrequest | local]`  
**默认值：** `fancyindex_header ""`  
**上下文：** `http`、`server`、`location`  
**描述：** 指定插入到目录列表顶部的文件。如果设置为空字符串，则发送模块提供的默认页眉。
可选参数指明 `path` 是作为 URI 通过子请求加载（默认），还是指向本地文件。

> **注意：** 使用该指令需要 Nginx 内置了 ngx_http_addition_module。

### fancyindex_show_path

**语法：** `fancyindex_show_path [on | off]`  
**默认值：** `fancyindex_show_path on`  
**上下文：** `http`、`server`、`location`  
**描述：** 是否在页眉之后输出路径以及闭合的 `</h1>` 标签。例如，当你希望用 PHP 脚本
处理路径显示时，这个选项会很有用。

> **警告：** 只有在通过 `fancyindex_header` 提供了自定义页眉时，才能关闭该指令。

### fancyindex_show_dotfiles

**语法：** `fancyindex_show_dotfiles [on | off]`  
**默认值：** `fancyindex_show_dotfiles off`  
**上下文：** `http`、`server`、`location`  
**描述：** 是否列出以点开头的文件。通常约定是隐藏这些文件。

### fancyindex_ignore

**语法：** `fancyindex_ignore string1 [string2 [... stringN]]`  
**默认值：** 无默认值。  
**上下文：** `http`、`server`、`location`  
**描述：** 指定不会显示在生成列表中的文件名列表。如果 Nginx 构建时启用了 PCRE 支持，
这些字符串会被当作正则表达式解释。

### fancyindex_hide_symlinks

**语法：** `fancyindex_hide_symlinks [on | off]`  
**默认值：** `fancyindex_hide_symlinks off`  
**上下文：** `http`、`server`、`location`  
**描述：** 启用后，生成的列表中不会包含符号链接。

### fancyindex_hide_parent_dir

**语法：** `fancyindex_hide_parent_dir [on | off]`  
**默认值：** `fancyindex_hide_parent_dir off`  
**上下文：** `http`、`server`、`location`  
**描述：** 启用后，不会显示上级目录。

### fancyindex_localtime

**语法：** `fancyindex_localtime [on | off]`  
**默认值：** `fancyindex_localtime off`  
**上下文：** `http`、`server`、`location`  
**描述：** 启用后以本地时间显示文件时间。默认值为“off”（GMT 时间）。

### fancyindex_language

**语法：** `fancyindex_language [en | zh_CN | auto]`  
**默认值：** `fancyindex_language en`  
**上下文：** `http`、`server`、`location`  
**描述：** 选择内置输出所使用的语言，包括模板标签以及星期、月份和 AM/PM 标记的名称。
设置为 `auto` 时会检查请求的 `Accept-Language` 头：包含 `zh` 时使用中文，否则使用英文。
通过 `fancyindex_header` 和 `fancyindex_footer` 提供的自定义页眉和页脚不受影响，
会按原样使用。

### fancyindex_time_format

**语法：** `fancyindex_time_format string`  
**默认值：** `fancyindex_time_format "%Y-%b-%d %H:%M"`  
**上下文：** `http`、`server`、`location`  
**描述：** 用于时间戳的格式字符串。格式说明符是
[strftime](https://linux.die.net/man/3/strftime) 函数所支持格式的一个子集，星期和月份名称
遵循 `fancyindex_language` 指令（默认英文）。支持的格式如下：

- `%a`：缩写的星期名称。
- `%A`：完整的星期名称。
- `%b`：缩写的月份名称。
- `%B`：完整的月份名称。
- `%d`：以十进制数表示的月内日期（范围 01 到 31）。
- `%e`：与 `%d` 类似，以十进制数表示月内日期，但前导零会被替换为空格。
- `%F`：等价于 `%Y-%m-%d`（ISO 8601 日期格式）。
- `%H`：以 24 小时制表示的十进制小时数（范围 00 到 23）。
- `%I`：以 12 小时制表示的十进制小时数（范围 01 到 12）。
- `%k`：以 24 小时制表示的十进制小时数（范围 0 到 23），个位数前会补一个空格。
- `%l`：以 12 小时制表示的十进制小时数（范围 1 到 12），个位数前会补一个空格。
- `%m`：以十进制数表示的月份（范围 01 到 12）。
- `%M`：以十进制数表示的分钟（范围 00 到 59）。
- `%p`：根据给定的时间值输出“AM”或“PM”（会按语言本地化）。
- `%P`：与 `%p` 类似，但使用小写形式：“am”或“pm”（会按语言本地化）。
- `%r`：使用上午/下午记法表示的时间，等价于 `%I:%M:%S %p`。
- `%R`：使用 24 小时制表示的时间（`%H:%M`）。
- `%S`：以十进制数表示的秒数（范围 00 到 60）。
- `%T`：使用 24 小时制表示的时间（`%H:%M:%S`）。
- `%u`：以十进制数表示的星期几，范围 1 到 7，星期一为 1。
- `%w`：以十进制数表示的星期几，范围 0 到 6，星期一为 0。
- `%y`：不包含世纪的十进制年份（范围 00 到 99）。
- `%Y`：包含世纪的十进制年份。
