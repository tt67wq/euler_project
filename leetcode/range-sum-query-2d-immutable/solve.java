class NumMatrix {
        static int[][] data = new int[1050][1050];
        public NumMatrix(int[][] matrix) {
                if (matrix.length > 0) {
                        for (int i = 0; i < matrix.length; i++) {
                                int sum = 0;
                                for (int j = 1; j <= matrix[0].length; j++) {
                                        sum += matrix[i][j - 1];
                                        data[i][j] = sum;
                                }
                        }
                }
        }
        public int sumRegion(int row1, int col1, int row2, int col2) {
                int sum = 0;
                for (int i = row1; i <= row2; i++) {
                        sum += data[i][col2 + 1] - data[i][col1];
                }
                return sum;
        }
}
