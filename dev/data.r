library(gapminder)
library(dplyr)

gapminder <- gapminder %>%
  filter(year == 2007, continent == "Americas")

x <- matrix(NA, nrow = nrow(gapminder), ncol = 2)

x[, 1] <- 1L
x[, 2] <- gapminder$gdpPercap

rownames(x) <- gapminder$country
colnames(x) <- c("Intercept", "GDP_per_capita")

y <- matrix(gapminder$lifeExp, ncol = 1)
rownames(y) <- gapminder$country
colnames(y) <- "Life_expectancy"

gapminder_am07 <- list(y = y, x = x)

try(dir.create("inst/extdata/data"))
save(gapminder_am07, file = "inst/extdata/data/gapminder_am07.RData")
