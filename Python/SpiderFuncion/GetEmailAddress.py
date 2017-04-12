#coding=utf-8
"""
*文件说明:获取页面中的邮箱地址
*作者:高小调
*创建时间:2017年04月12日 星期三 18时16分13秒
*开发环境:Kali Linux/Python v2.7.13
"""
#原文:http://blog.csdn.net/abvedu/article/details/54837188
#对原文中程序做了小小的改动

import requests,re
#获取邮箱地址
def GetEmailAddress(url):
    regex = r"([\w]+@[\w]+\.[cn|com|com\.cn|net]+)"
    html = requests.get(url).text
    emails = re.findall(regex,html)
    return emails

#获取该url中所有邮箱并打印
url = "http://tieba.baidu.com/p/5025823967?pn=3"
emails = GetEmailAddress(url)
i = 0
for email in emails:
    i += 1
    print("{}:{}".format(i,email))
