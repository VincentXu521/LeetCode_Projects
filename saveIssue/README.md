## **用nodejs抓取github上某仓库的某条issue明细**

> 说明：
>
> 利用官方自带api: GET /repos/:owner/:repo/issues

* ### node.js : 

  ##### 1. request;

  ##### 2. fs;

* ### python : 

  ##### 1. os;

  ##### 2. sys;

> 文件说明：
>
> saveIssue.js：是抓取一条issue到指定目录；
>
> ShellNodeJS.py：是命令行串行运行多条saveIssue.js脚本；
>
> 两个文件都用了命令行参数，
>
> saveIssue.js：中命令行参数是特定user特定repo的第几个issue；
>
> ShellNodeJS.py：中命令行参数是起始的第一个issue，运行**60**个；
>
> (因为 api.github.com 访问有 rate limit -- 需要认证解决)
>
> leetcode_solutions：中存了抓取的issues；

### 使用：

> npm init
>
> npm install ...

> **node saveIssue.js *argv*** run js;

> **python ShellNodeJS.py *argv*** run py;

### 抓取内容：

> 本文抓取的是grandyang的leetcode仓库下的issues；
>
> 改用需更改saveIssue.js文件中的url；



### 补充：

> img: 该文件夹中包括了Contents.md中需要的图片；
>
> changeLinks.py: 将Contents.md中的链接替换；
>
> Contents.md: 替换后的文件；-- 是grandyang博主题解目录；
>
> Contents - 原.md: 原文件内容；

