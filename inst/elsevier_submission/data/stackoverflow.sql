SELECT 
  YEAR(Posts.CreationDate) AS Year,
  COUNT(CASE WHEN Tags.TagName = 'r' THEN 1 END) AS r_questions,
  COUNT(*) AS total_questions,
  (COUNT(CASE WHEN Tags.TagName = 'r' THEN 1 END) * 100.0 / COUNT(*)) AS r_percentage
FROM Posts
JOIN PostTags ON Posts.Id = PostTags.PostId
JOIN Tags ON PostTags.TagId = Tags.Id
WHERE Posts.CreationDate BETWEEN DATEADD(YEAR, -20, GETDATE()) AND GETDATE()
  AND Posts.PostTypeId = 1
GROUP BY YEAR(Posts.CreationDate)
ORDER BY Year;
