## Huffman Coding
#### Goal: 문자열을 binary code로 lossless하게 전환할 수 있도록 각 문자에 맞는 최적의 code를 찾는다
#### 주로 문자는 1개당 1바이트 단위(8bit)로 저장되는데 더 적은 단위의 bit로 압축(compression)하는 방법을 찾는 것이다
<br/>

#### Implementation
##### 1. 파일에서 문자열을 읽어서 각 문자(symbol) 당 빈도수(freq)를 저장한다
##### 2. 각 문자와 빈도수를 저장하는 single node들의 tree를 만든다
##### 3. greedy한 방식으로 가장 빈도 수가 작은 노드를 u, v로 설정하고 이를 child로 갖는 w 노드로 merge 한다
##### 4. 1개의 root node가 남을 때까지 3번을 반복한다
##### 5. root로부터 왼쪽으로 갈 때마다 0, 오른쪽으로 갈 때마다 1로 간주하여 각 leaf node에 있는 symbol이 대체될 binary code를 찾는다

![Huffman.png](https://github.com/namkidong98/Study_Algorithm/blob/main/Huffman%20Coding/Huffman.PNG)
