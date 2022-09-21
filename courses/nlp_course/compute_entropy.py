import numpy as np
import os
from math import log, e
import re
from tqdm import tqdm
import jieba

class Vocabulary():
    def __init__(self):
        self.label_set = set()
        self.defined_label2id_dict = dict()
        self.label2id_dict = {}
        self.id2label_dict = {}

    def __len__(self):
        return len(self.label_set)

    def add(self, label):
        self.label_set.add(label)

    def add_sequence(self, labels):
        for label in labels:
            self.add(label)

    def add_dict(self, defined_label2id_dict):
        # TODO:Resolve dictionary key value pair conflicts situation
        # TODO:Resolve different names have same id
        for label, id in defined_label2id_dict.items():
            if label not in self.defined_label2id_dict:
                self.defined_label2id_dict[label] = id
                self.label_set.add(label)

    def create(self):
        label_list = list(self.label_set)
        label_list.sort()
        defined_label_set = set()
        for label, id in self.defined_label2id_dict.items():
            self.label2id_dict[label] = id
            self.id2label_dict[id] = label
            defined_label_set.add(label)
            if id >= len(label_list) or id < 0:
                raise IndexError("Defined dict id must smaller than label num and bigger than 0.")
        inserting_label_set = self.label_set - defined_label_set
        inserting_label_list = list(inserting_label_set)
        inserting_label_list.sort()
        inserting_index = 0
        for id in range(len(self.label_set)):
            if id not in self.id2label_dict.keys():
                self.label2id_dict[inserting_label_list[inserting_index]] = id
                self.id2label_dict[id] = inserting_label_list[inserting_index]
                inserting_index += 1
        self.label2id_dict = dict(sorted(self.label2id_dict.items(), key=lambda x: x[1]))
        self.id2label_dict = dict(sorted(self.id2label_dict.items(), key=lambda x: x[0]))

    def label2id(self, word):
        return self.label2id_dict[word]

    def id2label(self, id):
        return self.id2label_dict[id]

    def labels2ids(self, words):
        return [self.label2id(word) for word in words]

    def ids2labels(self, ids):
        return [self.id2label(id) for id in ids]

    def get_label2id_dict(self):
        return self.label2id_dict

    def get_id2label_dict(self):
        return self.id2label_dict

def entropy2(labels, base=None):
  """ Computes entropy of label distribution. """

  n_labels = len(labels)

  if n_labels <= 1:
    return 0

  value,counts = np.unique(labels, return_counts=True)
  probs = counts / n_labels
  n_classes = np.count_nonzero(probs)

  if n_classes <= 1:
    return 0

  ent = 0.

  # Compute entropy
  base = e if base is None else base
  for i in probs:
    ent -= i * log(i, base)

  return ent


# novel_path = "./new_novels"
# novel_files = os.listdir(novel_path)
# all_words = []
# vocab = Vocabulary()
# for novel_file in tqdm(novel_files):
#     with open(os.path.join(novel_path, novel_file), "r", encoding='UTF-8') as f:
#         lines = f.readlines()
#         processed_lines = [line.rstrip() for line in lines]
#         for line in processed_lines:
#             line = re.sub('[^\u4e00-\u9fa5]+','',line)
#             all_words.extend(line)
#             vocab.add_sequence(line)
#
# print("{} words detected.".format(len(all_words)))
# print("Creating vocab...")
# vocab.create()
# print("Calculating entropy...")
# all_word_ids = list(map(vocab.label2id_dict.get,all_words))
# entropy_result = entropy2(all_word_ids)
# print(entropy_result)

import pandas as pd
baike_file = r"baike/data-baike.xlsx"
df = pd.read_excel(baike_file,index_col=0)
all_words = []
vocab = Vocabulary()

novel_path = "./new_novels"
novel_files = os.listdir(novel_path)
for novel_file in tqdm(novel_files):
    with open(os.path.join(novel_path, novel_file), "r", encoding='UTF-8') as f:
        lines = f.readlines()
        processed_lines = [line.rstrip() for line in lines]
        for line in processed_lines:
            line = re.sub('[^\u4e00-\u9fa5]+','',line)
            seg_generator = jieba.cut("".join(line),use_paddle=True)
            seg_list = list(seg_generator)
            all_words.extend(seg_list)
            vocab.add_sequence(seg_list)

for idx,row in tqdm(df.iterrows(),total=df.shape[0]):
    # if idx >= 500:
    #     break
    text_piece = row["text"]
    if(isinstance(text_piece,str)):
        text_piece = re.sub('[^\u4e00-\u9fa5]+', '', text_piece)
        seg_generator = jieba.cut("".join(text_piece),use_paddle=True)
        # print("/".join(seg_list))
        seg_list = list(seg_generator)
        all_words.extend(seg_list)
        vocab.add_sequence(seg_list)
    # break

print("{} words detected.".format(len(all_words)))
print("Creating vocab...")
vocab.create()
print("Calculating entropy...")
all_word_ids = list(map(vocab.label2id_dict.get,all_words))
entropy_result = entropy2(all_word_ids)
print(entropy_result)