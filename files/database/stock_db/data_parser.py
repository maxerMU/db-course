import requests
from bs4 import BeautifulSoup

url = "https://www.avtozapchasty.ru/article/tgr_article_list.php"

response = requests.get(url)

webpage = response.content

soup = BeautifulSoup(webpage, "html.parser")

part_types = []
for part_type in soup.find_all("h2", id="neoroginal_title"):
    part_types.append(part_type.get_text())

print(part_types)

details = []
for details_group in soup.find_all("div", class_="columns"):
    group = []
    for detail in details_group.find_all("a"):
        group.append(detail.get_text().strip().replace("/ ", ""))
    
    details += group

print(details)