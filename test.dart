class TrieNode {
  late String character;
  bool isEnd = false;
  List<TrieNode> children = [];
  TrieNode({required this.character});

  void addWord(String word) {
    TrieNode child;
    String firstChar = word[0];

    TrieNode t = getChild(firstChar);

    if (t.character == '\$') {
      child = TrieNode(character: firstChar);
      children.add(child);
    } else {
      child = t;
    }

    if (word.length > 1) {
      child.addWord(word.substring(1));
    } else {
      child.isEnd = true;
    }
  }

  TrieNode getChild(String c) {
    for (TrieNode t in children) {
      if (t.character == c) {
        return t;
      }
    }
    return TrieNode(character: '\$');
  }
}

class Trie {
  late TrieNode root;

  Trie(List<String> words) {
    root = TrieNode(character: '\$');
    for (String word in words) {
      root.addWord(word);
    }
  }

  bool containsExact(String prefix, bool exact) {
    TrieNode lastNode = root;
    int i = 0;
    for (i = 0; i < prefix.length; i++) {
      lastNode = lastNode.getChild(prefix[i]);
      if (lastNode.character == '\$') {
        return false;
      }
    }

    return !exact || lastNode.isEnd;
  }
}
