import java.util.Scanner;

public class t1005 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int input = sc.nextInt();
        int[] stones = new int[input];
        int sum = 0;

        for (int j = 0; j <= stones.length - 1; j++) {
            stones[j] = sc.nextInt();
        }

        for (int i = 0; i < stones.length; i++) {
            sum = sum + stones[i];
        }

        int half = sum / 2;
        int[] dp = new int[half + 1];
        dp[0] = 1;

        for (int i = 0; i < stones.length; i++) {
            for (int j = half; j >= stones[i]; j--) {
                dp[j] = dp[j] | dp[j - stones[i]];
            }
        }

        for (int i = half; i >= 0; i--) {
            if (dp[i] == 1) {
                half = i;
                break;
            }
        }

        int min_diff = sum - 2 * half;
        System.out.println(min_diff);
    }
}
