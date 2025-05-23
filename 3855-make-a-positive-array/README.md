<h2><a href="https://leetcode.com/problems/make-a-positive-array">Make a Positive Array</a></h2> <img src='https://img.shields.io/badge/Difficulty-Medium-orange' alt='Difficulty: Medium' /><hr><p>You are given an array <code>nums</code>. An array is considered <strong>positive</strong> if the sum of all numbers in each <strong><span data-keyword="subarray">subarray</span></strong> with <strong>more than two</strong> elements is positive.</p>

<p>You can perform the following operation any number of times:</p>

<ul>
	<li>Replace <strong>one</strong> element in <code>nums</code> with any integer between -10<sup>18</sup> and 10<sup>18</sup>.</li>
</ul>

<p>Find the <strong>minimum</strong> number of operations needed to make <code>nums</code> <strong>positive</strong>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">nums = [-10,15,-12]</span></p>

<p><strong>Output:</strong> <span class="example-io">1</span></p>

<p><strong>Explanation:</strong></p>

<p>The only subarray with more than 2 elements is the array itself. The sum of all elements is <code>(-10) + 15 + (-12) = -7</code>. By replacing <code>nums[0]</code> with 0, the new sum becomes <code>0 + 15 + (-12) = 3</code>. Thus, the array is now positive.</p>
</div>

<p><strong class="example">Example 2:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">nums = [-1,-2,3,-1,2,6]</span></p>

<p><strong>Output:</strong> <span class="example-io">1</span></p>

<p><strong>Explanation:</strong></p>

<p>The only subarrays with more than 2 elements and a non-positive sum are:</p>

<table style="border: 1px solid black;">
	<tbody>
		<tr>
			<th style="border: 1px solid black;">Subarray Indices</th>
			<th style="border: 1px solid black;">Subarray</th>
			<th style="border: 1px solid black;">Sum</th>
			<th style="border: 1px solid black;">Subarray After Replacement (Set nums[1] = 1)</th>
			<th style="border: 1px solid black;">New Sum</th>
		</tr>
		<tr>
			<td style="border: 1px solid black;">nums[0...2]</td>
			<td style="border: 1px solid black;">[-1, -2, 3]</td>
			<td style="border: 1px solid black;">0</td>
			<td style="border: 1px solid black;">[-1, 1, 3]</td>
			<td style="border: 1px solid black;">3</td>
		</tr>
		<tr>
			<td style="border: 1px solid black;">nums[0...3]</td>
			<td style="border: 1px solid black;">[-1, -2, 3, -1]</td>
			<td style="border: 1px solid black;">-1</td>
			<td style="border: 1px solid black;">[-1, 1, 3, -1]</td>
			<td style="border: 1px solid black;">2</td>
		</tr>
		<tr>
			<td style="border: 1px solid black;">nums[1...3]</td>
			<td style="border: 1px solid black;">[-2, 3, -1]</td>
			<td style="border: 1px solid black;">0</td>
			<td style="border: 1px solid black;">[1, 3, -1]</td>
			<td style="border: 1px solid black;">3</td>
		</tr>
	</tbody>
</table>

<p>Thus, <code>nums</code> is positive after one operation.</p>
</div>

<p><strong class="example">Example 3:</strong></p>

<div class="example-block">
<p><strong>Input:</strong> <span class="example-io">nums = [1,2,3]</span></p>

<p><strong>Output:</strong> <span class="example-io">0</span></p>

<p><strong>Explanation:</strong></p>

<p>The array is already positive, so no operations are needed.</p>
</div>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>3 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>-10<sup>9</sup> &lt;= nums[i] &lt;= 10<sup>9</sup></code></li>
</ul>
