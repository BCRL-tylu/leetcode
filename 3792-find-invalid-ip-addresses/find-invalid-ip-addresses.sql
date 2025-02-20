SELECT ip, COUNT(*) AS invalid_count
FROM logs
WHERE ip REGEXP '\\.0|\\b([3-9][0-9][0-9]|2[6-9][0-9]|25[6-9])\\b|^(?:[^.]+\\.){0,2}[^.]+$|^(?:[^.]+\\.){4,}[^.]+$'
GROUP BY ip
ORDER BY invalid_count DESC, ip DESC;