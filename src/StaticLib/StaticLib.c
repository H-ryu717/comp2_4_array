#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include <stdlib.h>		// malloc, free
#include <stdbool.h>	// bool

#include "../include/lib_func.h"

// my_array を要素数nで初期化する
void initialize(my_array* ar, int n)
{
	if (ar == NULL) return;// NULLチェック

	if (n <= 0) { // 非正の値が来たら、とりあえず空にする
		ar->num = 0;
		ar->addr = NULL;
		return;
	}

	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);

	// 確保できなかったら要素数は0とする
	if (ar->addr == NULL) ar->num = 0;
}

// my_array を解放する
void release(my_array* ar)
{
	free(ar->addr);
	ar->addr = NULL;// 多重解放の防止
}

// my_array の要素数を変更する(以前の値は要素が同じ範囲で残す)
void resize(my_array* ar, int n)
{
	if (ar == NULL || n < 0) return; // 負のサイズは無視

	if (n == ar->num) return; // サイズが変わらない場合は何もしない

	// 新しいサイズに合わせて新しいメモリを確保
	int* newAddr = (int*)malloc(sizeof(int) * n);

	if (newAddr == NULL) return; // メモリ確保に失敗した場合は何もしない

	// コピーする要素数を決定（小さい方を採用）
	int copySize = (n < ar->num) ? n : ar->num;

	// 古いデータを新しいメモリにコピー
	for (int i = 0; i < copySize; ++i) {
		newAddr[i] = ar->addr[i];
	}

	// 古いメモリを解放
	free(ar->addr);

	// 新しいデータと要素数を設定
	ar->addr = newAddr;
	ar->num = n;
}

// my_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(my_array* ar, int index, int val)
{
	if (ar == NULL || index < 0) return false;

	// 配列を拡張
	if (index >= ar->num) {
		resize(ar, index + 1);
	}

	// 要素の設定
	ar->addr[index] = val;

	return true;
}

// my_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const my_array* ar, int index)
{
	if (ar == NULL || index < 0) return false;

	// 配列を拡張
	if (index >= ar->num) {
		resize(ar, index + 1);
	}

	// 要素の設定
	ar->addr[index] = val;

	return true;
}

// my_array の要素数を取得する
int size(const my_array* ar)
{
	if (ar == NULL) {
		return 0;
	}

	return ar->num;
}