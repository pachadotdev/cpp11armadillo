x <- as.matrix(mtcars[, -1])

# cyl gear and carb are categorical variables
str(mtcars)
unique(mtcars$cyl)
unique(mtcars$gear)
unique(mtcars$carb)

# add new column to x
x <- cbind(x, cyl4 = as.numeric(mtcars$cyl == 4))
x <- cbind(x, cyl6 = as.numeric(mtcars$cyl == 6))
x <- cbind(x, cyl8 = as.numeric(mtcars$cyl == 8))
x <- x[, !(colnames(x) == "cyl")]

x <- cbind(x, gear3 = as.numeric(mtcars$gear == 3))
x <- cbind(x, gear4 = as.numeric(mtcars$gear == 4))
x <- cbind(x, gear5 = as.numeric(mtcars$gear == 5))
x <- x[, !(colnames(x) == "gear")]

x <- cbind(x, carb1 = as.numeric(mtcars$carb == 1))
x <- cbind(x, carb2 = as.numeric(mtcars$carb == 2))
x <- cbind(x, carb3 = as.numeric(mtcars$carb == 3))
x <- cbind(x, carb4 = as.numeric(mtcars$carb == 4))
x <- cbind(x, carb6 = as.numeric(mtcars$carb == 6))
x <- cbind(x, carb8 = as.numeric(mtcars$carb == 8))
x <- x[, !(colnames(x) == "carb")]

y <- matrix(mtcars[, 1])
colnames(y) <- "mpg"
rownames(y) <- rownames(mtcars)

dim(x)
dim(y)

mtcars_mat <- list(x = x, y = y)

use_data(mtcars_mat, overwrite = TRUE)
