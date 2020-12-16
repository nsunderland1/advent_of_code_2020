open Core;;
let (=) = Poly.(=)
let (<>) = Poly.(<>)

let ignore_empty_lines = true

let parse_line line =
  let open Angstrom in
  let parse parser = Result.ok_or_failwith (parse_string ~consume:All parser line) in
  let integer =
    take_while1 (function '0' .. '9' -> true | _ -> false) >>| int_of_string
  in
  let lowercase =
    take_while1 (function 'a' .. 'z' -> true | _ -> false)
  in
  let parser = (fun lo hi c pass-> (lo, hi, c, pass)) <$> integer <* char '-' <*> integer <* char ' ' <*> any_char <* string ": " <*> lowercase in
  parse parser 

let int_out some_int =
   print_endline "";
   Out_channel.output_string stdout (string_of_int some_int)

(* let validate (lo, hi, c, pass) =
  let count = String.count ~f:(fun ch -> ch = c) pass in
  lo <= count && count <= hi *)

let validate (lo, hi, c, pass) =
  (String.get pass (lo-1) = c) <> (String.get pass (hi-1) = c)

let _ =
  let lines = In_channel.read_lines "input" in
  let lines = if ignore_empty_lines then List.filter ~f:(fun line -> not (phys_equal line "")) lines else lines in
  let data = List.map ~f:parse_line lines in
  int_out (List.count ~f:validate data)
