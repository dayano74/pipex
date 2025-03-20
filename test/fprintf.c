#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 簡易版 fprintf の再実装（my_fprintfと命名）
int	my_fprintf(FILE *stream, const char *format, ...)
{
	va_list		args;
	const char	*p = format;
	int			d;
	char		buffer[32];
	int			len;
	char		*str;

	va_start(args, format);
	int total_written = 0; // 出力した文字数の合計
	// 書式文字列を1文字ずつ走査
	while (*p != '\0')
	{
		if (*p == '%')
		{        // 書式指定子の開始
			p++; // '%' の次の文字を確認
			if (*p == 'd')
			{ // 整数型
				d = va_arg(args, int);
				len = snprintf(buffer, sizeof(buffer), "%d", d);
				fputs(buffer, stream);
				total_written += len;
			}
			else if (*p == 's')
			{ // 文字列型
				str = va_arg(args, char *);
				fputs(str, stream);
				total_written += strlen(str);
			}
			else if (*p == '%')
			{ // リテラルの '%'
				fputc('%', stream);
				total_written++;
			}
			else
			{
				// 未対応の書式指定子の場合はそのまま出力
				fputc('%', stream);
				fputc(*p, stream);
				total_written += 2;
			}
			p++; // 書式指定子の文字を処理済みとして次に進む
		}
		else
		{
			// 書式指定子でない通常の文字はそのまま出力
			fputc(*p, stream);
			total_written++;
			p++;
		}
	}
	va_end(args);
	return (total_written);
}

#include <stdio.h>

int	main(void)
{
	// my_fprintf を使用して、標準出力に書式付きの文字列を出力
	my_fprintf(stdout, "Hello, %s! Your score is %d%%.\n", "Alice", 90);
	return (0);
}
