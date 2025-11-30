
'''
TITLE: NLP text classification using scikit-learn

OBJECTIVE:
    -> To learn NLP workflow which include Text processing, TF_IDF vectorization, fearure extraction.

'''
# Lab 10: NLP Text Classification using scikit-learn

from sklearn.feature_extraction.text import TfidfVectorizer

from sklearn.model_selection import train_test_split

from sklearn.naive_bayes import MultinomialNB

from sklearn.metrics import accuracy_score, classification_report

# Sample dataset: Documents and labels

documents = [

   "I love programming in Python",

   "Python is great for data science",

   "I hate spam emails",

   "Spam messages are annoying",

   "Machine learning is fascinating",

   "I enjoy learning AI and NLP",

   "Buy now! Limited offer!",

   "This is a spam message"

]

labels = ["ham", "ham", "ham", "ham", "ham", "ham", "spam", "spam"]

# Step 1: Split dataset

X_train, X_test, y_train, y_test = train_test_split(

   documents, labels, test_size=0.25, random_state=42

)

# Step 2: TF-IDF Vectorization

vectorizer = TfidfVectorizer()

X_train_tfidf = vectorizer.fit_transform(X_train)

X_test_tfidf = vectorizer.transform(X_test)

# Step 3: Train Naive Bayes Classifier

clf = MultinomialNB()

clf.fit(X_train_tfidf, y_train)

# Step 4: Predict on test set

y_pred = clf.predict(X_test_tfidf)

# Step 5: Evaluate performance

print("Accuracy:", accuracy_score(y_test, y_pred))

print("\nClassification Report:\n", classification_report(y_test, y_pred))

# Step 6: Test new sentences

test_sentences = [

   "Python programming is fun",

   "Get free prizes now",

   "Learn AI and NLP"

]

test_tfidf = vectorizer.transform(test_sentences)

predictions = clf.predict(test_tfidf)

for sentence, label in zip(test_sentences, predictions):

   print(f"'{sentence}' => {label}")

