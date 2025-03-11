class Solution {
    public String applySubstitutions(List<List<String>> replacements, String text) {
        boolean modified = true;
        while (modified) {
            modified=false;
            for (List<String> replacement : replacements) {
                if (text.contains('%' + replacement.get(0) + '%')) {
                    modified = true;
                    text = text.replace('%' + replacement.get(0) + '%', replacement.get(1));
                }
            }
        }
        return text;
    }
}