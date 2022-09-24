import numpy as np
import os
from math import log, e
import re
from tqdm import tqdm
import jieba
import pandas as pd
from nltk import word_tokenize
import argparse

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
        # for label in labels:
        #     self.add(label)
        self.label_set = self.label_set.union(set(labels))

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

def cal_entropy(labels, base=None):
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


def read_baike(baike_file,mode="character",debug=False):
    if mode not in ["character","word"]:
        raise ValueError("Mode {} is not supported!".format(mode))
    df = pd.read_excel(baike_file, index_col=0)
    all_words = []
    for idx, row in tqdm(df.iterrows(), total=df.shape[0]):
        if debug:
            if idx >= 500:
                break
        text_piece = row["text"]
        if (isinstance(text_piece, str)):
            text_piece = re.sub('[^\u4e00-\u9fa5]+', '', text_piece)
            if mode == "word":
                seg_generator = jieba.cut("".join(text_piece), use_paddle=True)
                seg_list = list(seg_generator)
                all_words.extend(seg_list)
            if mode == "character":
                character_list = list(text_piece)
                all_words.extend(character_list)
    return all_words

def read_novels(novel_path,mode="character",debug=False):
    if mode not in ["character","word"]:
        raise ValueError("Mode {} is not supported!".format(mode))
    novel_files = os.listdir(novel_path)
    all_words = []
    for novel_file in tqdm(novel_files):
        with open(os.path.join(novel_path, novel_file), "r", encoding='UTF-8') as f:
            lines = f.readlines()
            processed_lines = [line.rstrip() for line in lines]
            for line in processed_lines:
                text_piece = re.sub('[^\u4e00-\u9fa5]+','',line)
                if mode == "word":
                    seg_generator = jieba.cut("".join(text_piece), use_paddle=True)
                    seg_list = list(seg_generator)
                    all_words.extend(seg_list)
                if mode == "character":
                    character_list = list(text_piece)
                    all_words.extend(character_list)
        if debug:
            break
    return all_words

def read_english_novels(novel_path,mode="character",debug=False):
    if mode not in ["character","word"]:
        raise ValueError("Mode {} is not supported!".format(mode))
    novel_files = os.listdir(novel_path)
    all_words = []
    for novel_file in tqdm(novel_files):
        with open(os.path.join(novel_path, novel_file), "r", encoding='UTF-8') as f:
            lines = f.readlines()
            processed_lines = [line.rstrip() for line in lines]
            for line in processed_lines:
                if mode == 'word':
                    text_piece = word_tokenize(line)
                    result = list(filter(lambda ele: re.search("[a-zA-Z\s]+", ele) is not None, text_piece))
                    result = list(map(lambda x: x.lower(),result))
                    all_words.extend(list(result))
                if mode == 'character':
                    text_piece = re.sub('[^a-zA-Z]+','',line)
                    all_words.extend(list(text_piece))
        if debug:
            break
    return all_words

def cal_entropy_of_words(words_list):
    vocab = Vocabulary()
    vocab.add_sequence(words_list)
    vocab.create()
    all_word_ids = list(map(vocab.label2id_dict.get,words_list))
    entropy_result = cal_entropy(all_word_ids)
    return entropy_result

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Entropy computing parameters')

    parser.add_argument("-l",'--language',type=str,help='language can be chinese or english',default='english')
    parser.add_argument('-d','--datapath', type=str, help='data source', required=True)
    parser.add_argument('-m','--mode',type=str,help='mode can be character or word',default='character',)
    parser.add_argument('-p','--percentage',type=float,help="the proportion of all the texts used",default=1)
    args = vars(parser.parse_args())
    print(args)

    language = args["language"]
    datapath = args["datapath"]
    mode = args["mode"]
    percentage = args["percentage"]
    if language not in ["english","chinese"]:
        raise ValueError("Language {} is not supported!".format(language))
    if mode not in ["character","word"]:
        raise ValueError("Mode {} is not supported!".format(mode))
    assert percentage <= 1 and percentage >= 0

    mapping = {"chinese":read_novels,"english":read_english_novels}

    print("Reading files for language {} in mode {}...".format(language,mode))
    func = mapping[language]
    all_words = func(datapath,mode)
    print("Calculating entropy for language {} in mode {}...".format(language,mode))
    some_words = all_words[:int(percentage * len(all_words))]
    entropy = cal_entropy(some_words)
    print("For language {} in mode {} using percentage {} the entropy is {}".format(language,mode,percentage,entropy))


    # baike_file = "baike/data-baike.xlsx"
    # novel_path = "new_novels"
    # english_novel_path = "english_novels"
    #
    # print("Reading files for english words entropy...")
    # all_english_letters = read_english_novels(english_novel_path,mode='word',debug=False)
    # print("Calculating english words entropy...")
    # english_letter_entropy = cal_entropy_of_words(all_english_letters)
    # print("English words entropy:",english_letter_entropy)
    #
    # print("Reading files for english letter entropy...")
    # all_english_letters = read_english_novels(english_novel_path,mode='character',debug=False)
    # print("Calculating english letter entropy...")
    # english_letter_entropy = cal_entropy_of_words(all_english_letters)
    # print("English letter entropy:",english_letter_entropy)
    #
    # # character entropy
    # print("Reading files for character entropy...")
    # all_baike_characters = read_baike(baike_file,mode="character",debug=False)
    # all_novel_characters = read_novels(novel_path,mode="character",debug=False)
    # print("Calculating character entropy...")
    # character_entropy = cal_entropy_of_words(all_novel_characters + all_baike_characters)
    # print("Chinese character entropy:", character_entropy)
    #
    # # word entropy
    # print("Reading files for word entropy...")
    # all_baike_words= read_baike(baike_file,mode="word",debug=False)
    # all_novel_words = read_novels(novel_path,mode="word",debug=False)
    # print("Calculating word entropy...")
    # word_entropy = cal_entropy_of_words(all_novel_words + all_baike_words)
    # print("Chinese word entropy:",word_entropy)
