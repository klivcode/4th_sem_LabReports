   
    
# =============================================================

# Lab 8: Naive Bayes Classifier for Text Classification

# =============================================================

# Goal: Classify text messages as "spam" or "ham" (not spam)

# Using the Naive Bayes probabilistic model.

# Key concepts:

# ✔ Tokenization (split text into words)

# ✔ Prior probability of classes

# ✔ Likelihood of words given class

# ✔ Laplace smoothing to handle unseen words

# =============================================================

import re

from collections import defaultdict

import math

# -------------------------------------------------------------

# Sample dataset: messages with labels

# -------------------------------------------------------------

data = [

   ("Win a free lottery ticket now", "spam"),

   ("Call your mom tonight", "ham"),

   ("Congratulations, you won a prize", "spam"),

   ("Let's have lunch tomorrow", "ham"),

   ("Claim your free gift now", "spam"),

   ("Can we meet today?", "ham")

]

# -------------------------------------------------------------

# Preprocessing function: Tokenize & lowercase

# -------------------------------------------------------------

def tokenize(text):

   """

   Converts text to lowercase and splits into words.

   Example: "Win a Free Gift" → ['win', 'a', 'free', 'gift']

   """

   text = text.lower()

   words = re.findall(r'\b\w+\b', text)  # Extract words only

   return words

# -------------------------------------------------------------

# Naive Bayes Classifier class

# -------------------------------------------------------------

class NaiveBayesClassifier:

   def __init__(self):

       self.classes = set()                   # Set of unique classes (spam, ham)

       self.word_counts = {}                  # Word frequency per class

       self.class_counts = {}                 # Number of messages per class

       self.vocab = set()                     # Vocabulary (all unique words)

       self.class_priors = {}                 # Prior probability of each class

   # ---------------------------------------------------------

   # Training the classifier

   # ---------------------------------------------------------

   def train(self, data):

       self.classes = set(label for _, label in data)  # Identify classes

       self.word_counts = {c: defaultdict(int) for c in self.classes}  # Initialize word counts

       self.class_counts = {c: 0 for c in self.classes}                # Initialize class counts

       for text, label in data:

           self.class_counts[label] += 1          # Count messages per class

           words = tokenize(text)                 # Tokenize the text

           for word in words:

               self.word_counts[label][word] += 1  # Count word occurrences

               self.vocab.add(word)                # Add to vocabulary

       # Compute prior probabilities P(class)

       total_docs = sum(self.class_counts.values())

       self.class_priors = {c: self.class_counts[c]/total_docs for c in self.classes}

   # ---------------------------------------------------------

   # Predicting class of new text

   # ---------------------------------------------------------

   def predict(self, text):

       words = tokenize(text)   # Tokenize input message

       scores = {}

       for c in self.classes:

           # Start with log prior probability of the class

           log_prob = math.log(self.class_priors[c])

           total_words = sum(self.word_counts[c].values())  # Total words in class

           # Add log likelihoods for each word

           for word in words:

               # Laplace smoothing: add 1 to avoid zero probability

               word_freq = self.word_counts[c].get(word, 0) + 1

               log_prob += math.log(word_freq / (total_words + len(self.vocab)))

           scores[c] = log_prob  # Store the score for this class

       # Return class with highest log probability

       return max(scores, key=scores.get)

# -------------------------------------------------------------

# Example usage

# -------------------------------------------------------------

if __name__ == "__main__":

   nb = NaiveBayesClassifier()

   nb.train(data)

   test_messages = [

       "Win a free gift",

       "Call me tomorrow",

       "Congratulations, you have won"

   ]

   for msg in test_messages:

       print(f"Message: '{msg}' => Predicted: {nb.predict(msg)}")













