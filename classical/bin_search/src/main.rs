fn binary_search<T: Ord>(arr: &[T], target: &T) -> i32 {
    let mut low = 0;
    let mut high = arr.len() as i32 - 1;

    while low <= high {
        let mid = (low + high) / 2;
        let mid_val = &arr[mid as usize];

        if mid_val == target {
            return mid;
        } else if mid_val > target {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    -1
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_binary_search_found() {
        let arr = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
        let target = 6;

        let result = binary_search(&arr, &target);
        assert_eq!(result, 5);
    }

    #[test]
    fn test_binary_search_not_found() {
        let arr = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
        let target = 10;

        let result = binary_search(&arr, &target);
        assert_eq!(result, -1);
    }

    #[test]
    fn test_binary_search_empty_array() {
        let arr: Vec<i32> = vec![];
        let target = 10;

        let result = binary_search(&arr, &target);
        assert_eq!(result, -1);
    }

    #[test]
    fn test_binary_search_single_element_array_found() {
        let arr = vec![10];
        let target = 10;

        let result = binary_search(&arr, &target);
        assert_eq!(result, 0);
    }

    #[test]
    fn test_binary_search_single_element_array_not_found() {
        let arr = vec![10];
        let target = 5;

        let result = binary_search(&arr, &target);
        assert_eq!(result, -1);
    }
}

// fn main() {
//     let arr = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
//     let target = 6;

//     let result = binary_search(&arr, &target);
//     println!("Target found at index: {}", result);
// }
