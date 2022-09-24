## 熵的计算
本文件夹下包含ucas NLP课程第一次作业的数据获取方式以及实验源代码。
### 数据爬取
使用[auto_scrape_novel.py](./auto_scrape_novel.py)爬取中文小说数据集，
使用[scrape_english.py](./scrape_english_novel.py)爬取英文小说数据集。

## 熵的计算
运行以下命令来复现实验结果
```shell
python compute_entropy.py -d chinese_novels/ -l chinese -m character
python compute_entropy.py -d chinese_novels/ -l chinese -m word
python compute_entropy.py -d english_novels/ -l english -m character
python compute_entropy.py -d english_novels/ -l english -m word
```
